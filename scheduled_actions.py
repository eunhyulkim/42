from apscheduler.schedulers.blocking import BlockingScheduler
from app import db, slack
from models import User, Match
from random import sample
import json
from blocks import get_base_blocks

sched = BlockingScheduler()


def match_failed_handling(unmatched_user):
    slack_id = unmatched_user.slack_id
    intra_id = unmatched_user.intra_id
    response = slack.conversations.open(users=slack_id, return_im=True)
    channel = response.body['channel']['id']
    blocks = get_base_blocks("MATCH FAILED. SORRY, " + str(intra_id) + "!")
    slack.chat.post_message(channel=channel, blocks=json.dumps(blocks))
    print("MATCH FAILED HANDLING")
    print("_SLACK_ID: " + str(slack_id))
    print("_BLOCK: " + str(blocks))
    return ("", 200)


def match_successed_handling(matches):
    print("MATCH SUCCESSED HANDLING")
    for match in matches:
        slack_id = [match.users[0].slack_id, match.users[1].slack_id]
        print("_SLACK_ID: " + str(slack_id[0]) + " & " + str(slack_id[1]))
        response = slack.conversations.open(users=slack_id, return_im=True)
        channel = response.body['channel']['id']
        blocks = get_base_blocks("MATCH SUCCESSED WITH " + str(match.users[0].intra_id) + " and " + str(match.users[1].intra_id) + "!")
        print("_BLOCK: " + str(blocks))
        slack.chat.post_message(channel=channel, blocks=json.dumps(blocks))
    return ("", 200)


def make_match():
    print("MAKE MATCH START")
    unmatched_users = User.query.filter_by(joined=True).all()
    matched_groups = []
    matches = []
    count_unmatched_users = len(unmatched_users)
    while count_unmatched_users >= 2:
        matched_group = sample(unmatched_users, 2)
        matched_groups += [matched_group]
        for i in range(2):
            unmatched_users.remove(matched_group[i])
        count_unmatched_users -= 2
    if count_unmatched_users == 1:
        unmatched_users[0].joined = False
        match_failed_handling(unmatched_users[0])
    for matched_group in matched_groups:
        matched_group[0].joined = False
        matched_group[1].joined = False
        match = Match(
            user1=matched_group[0],
            user2=matched_group[1]
        )
        matches.append(match)
    match_successed_handling(matches)
    db.session.add_all(matches)
    db.session.commit()
    return ("", 200)

sched.add_job(make_match, 'cron', hour=15, minute=00)

sched.start()